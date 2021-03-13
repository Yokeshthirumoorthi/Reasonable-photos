// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

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
