// Possible states for login model
type state =
  | NOT_LOGGED_IN
  | LOGIN_IN_PROGRESS
  | LOGIN_FULFILLED
  | LOGIN_REJECTED;

module AuthHook =
       (
         AuthProvider: AuthApi.ProviderInterface,
         ResponseHandler: AuthApi.ResponseHandlerInterface,
       ) => {
  // Custom React hook for login
  let useLogin = _ => {
    let (state, dispatch) = React.useState(() => NOT_LOGGED_IN);

    let onLoginSuccess = _ => dispatch(_ => LOGIN_FULFILLED);
    let onLoginFailure = _ => dispatch(_ => LOGIN_REJECTED);

    let login = (username, password) => {
      dispatch(_ => LOGIN_IN_PROGRESS);
      AuthProvider.login(username, password)
      ->Future.mapOk(ResponseHandler.transformLoginResponse)
      ->Future.tapOk(ResponseHandler.extractJwtDetails)
      ->Future.tapOk(onLoginSuccess)
      ->Future.tapError(onLoginFailure);
    };

    (login, state);
  };
};

module LoginHook =
  AuthHook((AuthApi.Make(Server.Make)), AuthApi.ResponseHandler);
