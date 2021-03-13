open ReactNative;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#F5FCFF",
          (),
        ),
    })
  );

[@react.component]
let app = () => {
  let appSettingsContextValue = AppSettings.useSettings();

  <AppSettings.ContextProvider value=appSettingsContextValue>
    <StatusBar barStyle=`darkContent />
    <View style=styles##container>
      
      <AuthComponent />
    </View>
  </AppSettings.ContextProvider>;
};
