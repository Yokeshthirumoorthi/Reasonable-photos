module LoginResponse = {
  [@decco]
  type t = {
    access: string,
    refresh: string,
  };

  let decode = json => t_decode(json)->Belt.Result.getExn;
};

module RefreshResponse = {
  [@decco]
  type t = {access: string};

  let decode = json => t_decode(json)->Belt.Result.getExn;
};

module type ResponseHandlerInterface = {
  let transformLoginResponse: Js.Json.t => LoginResponse.t;
  let transformRefreshResponse: Js.Json.t => RefreshResponse.t;
  let extractJwtDetails: LoginResponse.t => unit;
  let updateJwtDetails: RefreshResponse.t => unit;
};

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

module type Interface = {
  let login: (string, string) => Future.t(Result.t(LoginResponse.t, unit));
  let refreshAccessToken:
    string => Future.t(Result.t(RefreshResponse.t, unit));
};

module Make =
       (Server: Server.Interface, ResponseHandler: ResponseHandlerInterface) => {
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
