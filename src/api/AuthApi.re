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
    let auth: Session.t = {access: Some("abd"), refresh: None, errors: None};
    Ok(auth)->Future.value;
  };

  let logout = () => {
    Ok()->Future.value;
  };
};

module type ResponseHandlerInterface = {
  let transformLoginResponse: Js.Json.t => Session.t;
};

module ResponseHandler = {
  let transformLoginResponse = json => Session.decode(json);
};
