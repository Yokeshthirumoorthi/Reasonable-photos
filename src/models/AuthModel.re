// Possible states for login model
type t_login =
  | NOT_LOGGED_IN
  | LOGIN_IN_PROGRESS
  | LOGIN_FULFILLED(Session.t)
  | LOGIN_REJECTED(Session.t);

module type AuthProvider = {
  let login:
    (Session.username, Session.password) =>
    Future.t(Result.t(Session.t, Session.t));
};

module OwnPhotosAuthProvider: AuthProvider = {
  let login = (username: Session.username, password: Session.password) => {
    let auth: Session.t = {
      access: Some("abc"),
      refresh: Some("bcd"),
      errors: None,
    };

    Ok(auth)->Future.value;
  };
};

module AuthHook = (AuthProvider: AuthProvider) => {
  // Custom React hook for login
  let useLogin = _ => {
    let (state, dispatch) = React.useState(() => NOT_LOGGED_IN);

    let onLoginSuccess = auth => dispatch(_ => LOGIN_FULFILLED(auth));
    let onLoginFailure = auth => dispatch(_ => LOGIN_REJECTED(auth));

    let login = (username, password) => {
      dispatch(_ => LOGIN_IN_PROGRESS);
      AuthProvider.login(username, password)
      ->Future.tapOk(onLoginSuccess)
      ->Future.tapError(onLoginFailure);
    };

    (login, state);
  };
};

module LoginHook = AuthHook(OwnPhotosAuthProvider);
