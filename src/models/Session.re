module Token = {
  [@decco]
  type t = {
    exp: int,
    first_name: string,
    is_admin: bool,
    jti: string,
    last_name: string,
    name: string,
    scan_directory: string,
    token_type: string,
    user_id: int,
  };

  let default = {
    exp: 0,
    first_name: "",
    is_admin: false,
    jti: "",
    last_name: "",
    name: "",
    scan_directory: "",
    token_type: "",
    user_id: 0,
  };

  [@bs.module "./js/jwtDecoder.js"] [@bs.scope "default"]
  external jwtDecoder: string => Js.Json.t = "jwtDecoder";

  let decode = tokenString =>
    tokenString->jwtDecoder->t_decode->Belt.Result.getExn;
};

module TokenData = {
  [@bs.deriving abstract]
  type t = {mutable data: Token.t};
  let jwt = t(~data=Token.default);
  let setData = tokenString => jwt->dataSet(tokenString->Token.decode);
  let getData = _ => jwt->dataGet;
};

module Access_Token = TokenData;
module Refresh_Token = TokenData;
