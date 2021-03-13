// Copyright © 2021 Yokesh Thirumoorthi
// [This program is licensed under the "MIT License"]
// Please see the file LICENSE in the source
// distribution of this software for license terms.

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
    <View style=styles##container> <MainScreen /> </View>
  </AppSettings.ContextProvider>;
};
