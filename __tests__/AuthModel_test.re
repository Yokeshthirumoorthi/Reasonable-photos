// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

open Jest;
open Expect;

[@bs.module] external loginResponse: Js.Json.t = "../data/loginResponse.json";
[@bs.module]
external refreshTokenResponse: Js.Json.t = "../data/refreshTokenResponse.json";

module TestServer: Server.Interface = {
  let post = (apipath: string, _payload: Js.t('b)) => {
    switch (apipath) {
    | "/auth/token/obtain/" => Js.Promise.resolve(loginResponse)
    | "/auth/token/refresh/" => Js.Promise.resolve(refreshTokenResponse)
    | _ => failwith("Invalid Api Path")
    };
  };
  let get = (apipath: string) => {
    switch (apipath) {
    | "/auth/token/obtain/" => Js.Promise.resolve(loginResponse)
    | "/auth/token/refresh/" => Js.Promise.resolve(refreshTokenResponse)
    | _ => failwith("Invalid Api Path")
    };
  };
};

module Provider = AuthApi.Make(TestServer, AuthApi.ResponseHandler);

describe("Authentication", () => {
  testAsync("Login", finish => {
    let access_token: Auth.Token.t = {
      exp: 1615327775,
      first_name: "",
      is_admin: true,
      jti: "c648069d28e347319c1d8a1802b4fb8f",
      last_name: "",
      name: "admin",
      scan_directory: "/data/Pictures",
      token_type: "access",
      user_id: 1,
    };

    let refresh_token: Auth.Token.t = {
      exp: 1615932275,
      first_name: "",
      is_admin: true,
      jti: "73adf7d3aa1c48349993ba6f9394410c",
      last_name: "",
      name: "admin",
      scan_directory: "/data/Pictures",
      token_type: "refresh",
      user_id: 1,
    };

    Provider.login("a", "b")
    ->Future.tapOk(result => {
        Auth.Access_Token.getData()
        |> expect
        |> toEqual(access_token)
        |> finish;

        Auth.Refresh_Token.getData()
        |> expect
        |> toEqual(refresh_token)
        |> finish;
      })
    ->Future.tapError(_err => Js.log2("Login Test has failed", loginResponse))
    ->ignore;
  });
  testAsync("Refresh Token", finish => {
    let access_token: Auth.Token.t = {
      exp: 1615448163,
      first_name: "",
      is_admin: true,
      jti: "932d0d8537704e0aaba73722319a402d",
      last_name: "",
      name: "admin",
      scan_directory: "/data/Pictures",
      token_type: "access",
      user_id: 1,
    };

    let refresh_token: Auth.Token.t = {
      exp: 1615932275,
      first_name: "",
      is_admin: true,
      jti: "73adf7d3aa1c48349993ba6f9394410c",
      last_name: "",
      name: "admin",
      scan_directory: "/data/Pictures",
      token_type: "refresh",
      user_id: 1,
    };

    Provider.refreshAccessToken(Auth.Refresh_Token.getToken())
    ->Future.tapOk(result => {
        Auth.Access_Token.getData()
        |> expect
        |> toEqual(access_token)
        |> finish;

        Auth.Refresh_Token.getData()
        |> expect
        |> toEqual(refresh_token)
        |> finish;
      })
    ->Future.tapError(_err => Js.log2("Login Test has failed", loginResponse))
    ->ignore;
  });
});
