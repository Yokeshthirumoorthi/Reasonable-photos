// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

open ApiTypes;

/*****************************************************************
 * AUTHAPI INTERFACES
 ******************************************************************/
module type AuthApi = {
  let login: (string, string) => Future.t(Result.t(LoginResponse.t, unit));
  let refreshAccessToken:
    string => Future.t(Result.t(RefreshResponse.t, unit));
};

module type AuthApiResponseHandler = {
  let transformLoginResponse: Js.Json.t => LoginResponse.t;
  let transformRefreshResponse: Js.Json.t => RefreshResponse.t;
  let extractJwtDetails: LoginResponse.t => unit;
  let updateJwtDetails: RefreshResponse.t => unit;
};

/*****************************************************************
 * USERAPI INTERFACES
 ******************************************************************/
module type UserApi = {
  let fetchUserSelfDetails: int => Future.t(Result.t(User.t, unit));
};

module type UserApiResponseHandler = {
  let decodeUserResponse: Js.Json.t => User.t;
};
