open Expo;
open ReactNative;

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
