type username = string;
type password = string;
type email = string;
type firstname = string;
type lastname = string;
type token = option(string);

// Loing query response object structure
type auth = {
  access: token,
  refresh: token,
  errors: option(string),
};

// Possible states for login model
type t_login =
  | NOT_LOGGED_IN
  | LOGIN_IN_PROGRESS
  | LOGIN_FULFILLED(auth)
  | LOGIN_REJECTED(auth);

module type AuthApi = {
  let login: (username, password) => Future.t(Result.t(auth, auth));
};

module AuthApi = {
  let login = (username, password) => {
    let auth: auth = {
      access: Some("abc"),
      refresh: Some("bcd"),
      errors: None,
    };

    Ok(auth)->Future.value;
  };
};

module AuthService = (AuthApi: AuthApi) => {
  // Custom React hook for login
  let useLogin = _ => {
    let (state, dispatch) = React.useState(() => NOT_LOGGED_IN);

    let onLoginSuccess = auth => dispatch(_ => LOGIN_FULFILLED(auth));
    let onLoginFailure = auth => dispatch(_ => LOGIN_REJECTED(auth));

    let login = (username, password) => {
      dispatch(_ => LOGIN_IN_PROGRESS);
      AuthApi.login(username, password)
      ->Future.tapOk(onLoginSuccess)
      ->Future.tapError(onLoginFailure);
    };

    (login, state);
  };
};

module LoginService = AuthService(AuthApi);
