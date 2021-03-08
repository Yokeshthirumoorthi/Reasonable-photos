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
