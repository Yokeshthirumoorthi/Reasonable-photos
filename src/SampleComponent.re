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

module LinearGradientToggleButton = {
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

module TextModel = {
  type t =
    | WelcomeText(string)
    | IntroText(string);

  type action =
    | ShowWelcomeText
    | ShowIntroText;

  let reducer = (_state: t, action) =>
    switch (action) {
    | ShowIntroText => IntroText("Intro Message")
    | ShowWelcomeText => WelcomeText("Welcome Message")
    };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      TextModel.reducer,
      WelcomeText("Welcome Message from grocery"),
    );

  let handleToggleText = _ => {
    switch (state) {
    | WelcomeText(_) => dispatch(ShowIntroText)
    | IntroText(_) => dispatch(ShowWelcomeText)
    };
  };

  <>
    <LinearGradientToggleButton
      onPress=handleToggleText
      text={
        switch (state) {
        | WelcomeText(string) => string
        | IntroText(string) => string
        }
      }
      testID="toggle-button"
    />
    <Text style=styles##instructions>
      "CLICK TO TOGGLE MESSAGE"->React.string
    </Text>
  </>;
};
