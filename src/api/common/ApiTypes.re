// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

module LoginResponse = {
  [@decco]
  type t = {
    access: string,
    refresh: string,
  };

  let decode = json => t_decode(json)->Belt.Result.getExn;
};

module RefreshResponse = {
  [@decco]
  type t = {access: string};

  let decode = json => t_decode(json)->Belt.Result.getExn;
};

module User = {
  [@decco]
  type t = {
    id: int,
    username: string,
    email: option(string),
    scan_directory: option(string),
    first_name: option(string),
    last_name: string,
    public_photo_count: int,
    date_joined: string,
    avatar: option(string),
    photo_count: int,
  };

  let decode = json => t_decode(json)->Belt.Result.getExn;
};
