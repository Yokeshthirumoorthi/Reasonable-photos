type username = string;
type password = string;
type email = string;
type firstname = string;
type lastname = string;
type token = option(string);

// Loing query response object structure
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

module Decode = {
  open Json.Decode;

  let fromJSONString = (json): t => {
    access: json |> optional(field("access", string)),
    refresh: json |> optional(field("refresh", string)),
    errors: json |> optional(field("errors", string)),
  };
};

module User = {
  type t = {
    id: int,
    firstname,
  };

  let make = (id, firstname) => {id, firstname};

  let default = {id: 0, firstname: ""};

  module Decode = {
    open Json.Decode;

    let fromJSONString = (json): t => {
      id: json |> field("id", int),
      firstname: json |> field("firstname", string),
    };
  };
};
