open Jest;
open Expect;

[@bs.module]
external loginResponse: Js.Json.t = "../server/data/loginResponse.json";

module TestServer: Server.Interface = {
  let post = (apipath: string, _payload: Js.t('b)) => {
    Js.Promise.resolve(loginResponse);
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
  })
});
