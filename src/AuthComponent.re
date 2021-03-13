open ReactNative;
open Expo;

let styles =
  Style.(
    StyleSheet.create({
      "instructions": style(~textAlign=`center, ()),
      "permissionsLink":
        textStyle(
          ~flexShrink=1.,
          ~fontSize=14.,
          ~lineHeight=14. *. 1.4,
          ~fontWeight=`_600,
          (),
        ),
    })
  );

module LinearGradientButton = {
  [@react.component]
  let make = (~onPress, ~text, ~testID) => {
    <LinearGradient
      colors=[|"#DD4B39", "#C62C19"|]
      start=[|0.0, 0.0|]
      _end=[|1.0, 1.0|]
      style=Style.(style(~padding=dp(12.), ~borderRadius=12., ()))>
      <TouchableOpacity onPress testID>
        <Text style=Style.(array([|styles##permissionsLink|]))>
          text->React.string
        </Text>
      </TouchableOpacity>
    </LinearGradient>;
  };
};

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
