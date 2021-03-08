open Jest;
open Expect;

describe("Authentication", () => {
  testAsync("Login", finish => {
    let auth: AuthModel.auth = {
      access: Some("abc"),
      refresh: Some("bcd"),
      errors: None,
    };

    AuthModel.AuthApi.login("a", "b")
    ->Future.tapOk(result => result |> expect |> toEqual(auth) |> finish)
    ->Future.tapError(_err => Js.log2("Login Test has failed", auth))
    ->ignore;
  })
});
