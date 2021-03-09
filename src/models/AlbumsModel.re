type state =
  | EMPTY_THING_ALBUMS_LIST
  | FETCH_THING_ALBUMS_LIST
  | FETCH_THING_ALBUMS_LIST_FULFILLED(string)
  | FETCH_THING_ALBUMS_LIST_REJECTED(string);

module type AlbumsActionsInterface = {
  let fetchThingAlbumsList: unit => Future.t(result(string, 'a));
};

module Hooks = (AlbumsActions: AlbumsActionsInterface) => {
  let useFetchThingAlbumsList = _ => {
    let (state, dispatch) = React.useState(() => EMPTY_THING_ALBUMS_LIST);

    let onSuccess = data =>
      dispatch(_ => FETCH_THING_ALBUMS_LIST_FULFILLED(data));
    let onFailure = error =>
      dispatch(_ => FETCH_THING_ALBUMS_LIST_REJECTED(error));

    let fetchThingAlbumsList = () => {
      dispatch(_ => FETCH_THING_ALBUMS_LIST);
      AlbumsActions.fetchThingAlbumsList()
      ->Future.tapOk(onSuccess)
      ->Future.tapError(onFailure);
    };

    (fetchThingAlbumsList, state);
  };
};
