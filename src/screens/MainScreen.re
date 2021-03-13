// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

open ReactNative;

[@react.component]
let make = () => {
  let (login, _) = AuthModel.ReactHook.useLogin();
  let (refreshToken, _) = AuthModel.ReactHook.useRefreshToken();
  let (fetchUserSelfDetails, _) =
    UserModel.ReactHook.useFetchUserSelfDetails();

  let onLoginPress = _ =>
    login("admin", "admin")
    ->Future.tapOk(_result => {
        Js.log(Auth.Access_Token.getData());
        Js.log(Auth.Refresh_Token.getData());
      })
    ->Future.tapError(_err =>
        Alert.alert(
          ~title="Ooops, something bad happened",
          ~message=
            "Please report us this error with informations about your device so we can improve Reasonable Photos.",
          (),
        )
      )
    ->ignore;

  let onRefreshToken = _ =>
    refreshToken(Auth.Refresh_Token.getToken())
    ->Future.tapOk(_result => {
        Js.log(Auth.Access_Token.getData());
        Js.log(Auth.Refresh_Token.getData());
      })
    ->Future.tapError(_err =>
        Alert.alert(
          ~title="Ooops, something bad happened",
          ~message=
            "Please report us this error with informations about your device so we can improve Reasonable Photos.",
          (),
        )
      )
    ->ignore;

  let onFetchUserDetails = _ =>
    fetchUserSelfDetails(Auth.Refresh_Token.getData().user_id)
    ->Future.tapOk(result => {Js.log(result)})
    ->Future.tapError(_err =>
        Alert.alert(
          ~title="Ooops, something bad happened",
          ~message=
            "Please report us this error with informations about your device so we can improve Reasonable Photos.",
          (),
        )
      )
    ->ignore;

  <>
    <LinearGradientButton
      onPress=onLoginPress
      text="Login"
      testID="toggle-button"
    />
    <LinearGradientButton
      onPress=onRefreshToken
      text="Refresh"
      testID="refresh-button"
    />
    <LinearGradientButton
      onPress=onFetchUserDetails
      text="Fetch User"
      testID="user-button"
    />
  </>;
};
