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
  <>
    <StatusBar barStyle=`darkContent />
    <View style=styles##container>
      <SampleComponent />
      <AuthComponent />
    </View>
  </>;
};
