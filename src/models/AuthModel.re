// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

// Possible states for login model
type state =
  | NOT_LOGGED_IN
  | LOGIN_IN_PROGRESS
  | LOGIN_FULFILLED
  | LOGIN_REJECTED
  | TOKEN_NOT_REFRESHED
  | REFRESH_TOKEN_IN_PROGRESS
  | REFRESH_TOKEN_FULFILLED
  | REFRESH_TOKEN_REJECTED;

module Make = (AuthProvider: ApiInterfaces.AuthApi) => {
  // Custom React hook for login
  let useLogin = _ => {
    let (state, dispatch) = React.useState(() => NOT_LOGGED_IN);

    let onLoginSuccess = _ => dispatch(_ => LOGIN_FULFILLED);
    let onLoginFailure = _ => dispatch(_ => LOGIN_REJECTED);

    let login = (username, password) => {
      dispatch(_ => LOGIN_IN_PROGRESS);
      AuthProvider.login(username, password)
      ->Future.tapOk(onLoginSuccess)
      ->Future.tapError(onLoginFailure);
    };

    (login, state);
  };

  // Custom React hook for Token Refresh
  let useRefreshToken = _ => {
    let (state, dispatch) = React.useState(() => TOKEN_NOT_REFRESHED);

    let onLoginSuccess = _ => dispatch(_ => REFRESH_TOKEN_FULFILLED);
    let onLoginFailure = _ => dispatch(_ => REFRESH_TOKEN_REJECTED);

    let refreshToken = refresh_token => {
      dispatch(_ => REFRESH_TOKEN_IN_PROGRESS);
      AuthProvider.refreshAccessToken(refresh_token)
      ->Future.tapOk(onLoginSuccess)
      ->Future.tapError(onLoginFailure);
    };

    (refreshToken, state);
  };
};

module AuthProvider = AuthApi.Make(Server.Make, AuthApi.ResponseHandler);
module ReactHook = Make(AuthProvider);
