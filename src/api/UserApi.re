open ApiInterfaces;

module Make =
       (Server: Server.Interface, ResponseHandler: UserApiResponseHandler) => {
  // Get user details using userid
  let fetchUserSelfDetails = (userId: int) => {
    let handleError = error => Js.log(error);

    Server.get(ApiPath.fetchUserSelfDetails ++ userId->string_of_int)
    ->FutureJs.fromPromise(handleError)
    ->Future.mapOk(ResponseHandler.decodeUserResponse);
  };
};

/*****************************************************************
 * Response handler functions for Api calls
 ******************************************************************/
module ResponseHandler = {
  open ApiTypes;
  let decodeUserResponse = User.decode;
};
