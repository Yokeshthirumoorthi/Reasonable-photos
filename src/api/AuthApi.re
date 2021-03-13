open ApiTypes;
open ApiInterfaces;

module ResponseHandler = {
  let transformLoginResponse = json => LoginResponse.decode(json);
  let transformRefreshResponse = json => RefreshResponse.decode(json);

  let extractJwtDetails = (session: LoginResponse.t) => {
    session.access->Auth.Access_Token.setToken;
    session.access->Auth.Access_Token.setData;
    session.refresh->Auth.Refresh_Token.setToken;
    session.refresh->Auth.Refresh_Token.setData;
  };
  let updateJwtDetails = (session: RefreshResponse.t) => {
    session.access->Auth.Access_Token.setToken;
    session.access->Auth.Access_Token.setData;
  };
};

module Make =
       (Server: Server.Interface, ResponseHandler: AuthApiResponseHandler) => {
  let signup =
      (
        _username: string,
        _password: string,
        _email: string,
        _firstname: string,
        _lastname: string,
      ) => {
    let response = {}; // TODO: add response object
    Ok(response)->Future.value;
  };

  let login = (username: string, password: string) => {
    let handleError = error => Js.log(error);

    Server.post(
      "/auth/token/obtain/",
      {"username": username, "password": password},
    )
    ->FutureJs.fromPromise(handleError)
    ->Future.mapOk(ResponseHandler.transformLoginResponse)
    ->Future.tapOk(ResponseHandler.extractJwtDetails);
  };

  let refreshAccessToken = refresh_token => {
    let handleError = error => Js.log(error);
    Server.post("/auth/token/refresh/", {"refresh": refresh_token})
    ->FutureJs.fromPromise(handleError)
    ->Future.mapOk(ResponseHandler.transformRefreshResponse)
    ->Future.tapOk(ResponseHandler.updateJwtDetails);
  };

  let logout = () => {
    Ok()->Future.value;
  };
};
