module type ProviderInterface = {
  let login:
    (Session.username, Session.password) =>
    Future.t(Result.t(Js.Json.t, unit));
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

  let login = (username: Session.username, password: Session.password) => {
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

module type ResponseHandlerInterface = {
  let transformLoginResponse: Js.Json.t => Session.t;
  let extractJwtDetails: Session.t => unit;
};

module ResponseHandler = {
  // let jwtTokenDecoder = (token: string) => jwtDecoder(token);
  let transformLoginResponse = json => Session.decode(json);
  let extractJwtDetails = (session: Session.t) => {
    let accessTokenString = Option.getWithDefault(session.access, "");
    let accessTokenObj = accessTokenString->Session.Token.decode;
    accessTokenObj->Session.Access_Token.setData;

    let refreshTokenString = Option.getWithDefault(session.refresh, "");
    let refreshTokenObj = refreshTokenString->Session.Token.decode;
    refreshTokenObj->Session.Refresh_Token.setData;
  };
};
