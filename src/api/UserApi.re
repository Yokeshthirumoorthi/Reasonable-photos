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

module type ResponseHandlerInterface = {
  let decodeUserResponse: Js.Json.t => User.t;
};

module ResponseHandler = {
  let decodeUserResponse = User.decode;
};

module type Interface = {
  let fetchUserSelfDetails: int => Future.t(Result.t(User.t, unit));
};

module Make =
       (Server: Server.Interface, ResponseHandler: ResponseHandlerInterface) => {
  let fetchUserSelfDetails = (userId: int) => {
    let handleError = error => Js.log(error);

    Server.get("/user/" ++ userId->string_of_int)
    ->FutureJs.fromPromise(handleError)
    ->Future.mapOk(ResponseHandler.decodeUserResponse);
  };
};
