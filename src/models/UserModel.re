// Possible states for login model
type state =
  | FETCH_USER_SELF_DETAILS_NOT_STARTED
  | FETCH_USER_SELF_DETAILS
  | FETCH_USER_SELF_DETAILS_FULFILLED
  | FETCH_USER_SELF_DETAILS_REJECTED;

module UserHook = (UserProvider: ApiInterfaces.UserApi) => {
  // Custom React hook for login
  let useFetchUserSelfDetails = _ => {
    let (state, dispatch) =
      React.useState(() => FETCH_USER_SELF_DETAILS_NOT_STARTED);

    let onSuccess = _ => dispatch(_ => FETCH_USER_SELF_DETAILS_FULFILLED);
    let onFailure = _ => dispatch(_ => FETCH_USER_SELF_DETAILS_REJECTED);

    let fetchUserSelfDetails = userId => {
      dispatch(_ => FETCH_USER_SELF_DETAILS);
      UserProvider.fetchUserSelfDetails(userId)
      ->Future.tapOk(onSuccess)
      ->Future.tapError(onFailure);
    };

    (fetchUserSelfDetails, state);
  };
};

module FetchUserHook =
  UserHook((UserApi.Make(Server.Make, UserApi.ResponseHandler)));
