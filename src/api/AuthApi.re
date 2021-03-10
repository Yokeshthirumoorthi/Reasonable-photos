module type ProviderInterface = {
  let login: (string, string) => Future.t(Result.t(Js.Json.t, unit));
};

module Provider = {
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
    ->FutureJs.fromPromise(handleError);
  };

  let refreshAccessToken = (_token: string) => {
    // let auth: Session.t = {access: Some("abd"), refresh: None, errors: None};
    Ok()
    ->Future.value;
  };

  let logout = () => {
    Ok()->Future.value;
  };
};

module LoginResponse = {
  [@decco]
  type t = {
    access: string,
    refresh: string,
  };

  let decode = json => t_decode(json)->Belt.Result.getExn;
};

module type ResponseHandlerInterface = {
  let transformLoginResponse: Js.Json.t => LoginResponse.t;
  let extractJwtDetails: LoginResponse.t => unit;
};

module ResponseHandler = {
  let transformLoginResponse = json => LoginResponse.decode(json);

  let extractJwtDetails = (session: LoginResponse.t) => {
    session.access->Session.Access_Token.setData;
    session.refresh->Session.Refresh_Token.setData;
  };
};
