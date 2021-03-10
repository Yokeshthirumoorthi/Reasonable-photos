type username = string;
type password = string;
type email = string;
[@decco]
type firstname = string;
type lastname = string;
[@decco]
type token = option(string);

// Login query's response object structure
[@decco]
type t = {
  access: token,
  refresh: token,
  errors: option(string),
};

let make = (access, refresh) => {
  access: Some(access),
  refresh: Some(refresh),
  errors: None,
};

let default = {access: None, refresh: None, errors: None};

let decode = json => t_decode(json)->Belt.Result.getExn;

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

module Access_Token = {
  [@bs.deriving abstract]
  type t = {mutable data: Token.t};
  let jwt = t(~data=Token.default);
  let setData = jwt->dataSet;
  let getData = _ => jwt->dataGet;
};

module Refresh_Token = {
  [@bs.deriving abstract]
  type t = {mutable data: Token.t};
  let jwt = t(~data=Token.default);
  let setData = jwt->dataSet;
  let getData = _ => jwt->dataGet;
};

module User = {
  [@decco]
  type t = {
    id: int,
    firstname,
  };

  let make = (id, firstname) => {id, firstname};

  let default = {id: 0, firstname: ""};

  let decode = json => t_decode(json)->Belt.Result.getExn;
};
