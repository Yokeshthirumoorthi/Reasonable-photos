open ApiTypes;
open ApiInterfaces;

module ResponseHandler = {
  let decodeUserResponse = User.decode;
};

module Make =
       (Server: Server.Interface, ResponseHandler: UserApiResponseHandler) => {
  // Get user details using userid
  let fetchUserSelfDetails = (userId: int) => {
    let handleError = error => Js.log(error);

    Server.get("/user/" ++ userId->string_of_int)
    ->FutureJs.fromPromise(handleError)
    ->Future.mapOk(ResponseHandler.decodeUserResponse);
  };
};
