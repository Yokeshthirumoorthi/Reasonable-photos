type t = {
  auth: Session.t,
  user: Session.User.t,
  lastUpdated: float,
};

let defaultSettings = {
  auth: Session.default,
  user: Session.User.default,
  lastUpdated: 0.,
};

let decodeJsonSettingsOrRaise = (json: Js.Json.t): t =>
  Json.Decode.{
    auth: json |> field("auth", Session.Decode.fromJSONString),
    user: json |> field("user", Session.User.Decode.fromJSONString),
    lastUpdated: json |> field("lastUpdated", Json.Decode.float),
  };

let decodeJsonSettings = (json: Js.Json.t): Future.t(Result.t(t, string)) => {
  (
    try(Ok(json->decodeJsonSettingsOrRaise)) {
    | Json.Decode.DecodeError(_exn) =>
      Js.log(_exn);
      Error("Ooops! Something went wrong when loading settings");
    }
  )
  ->Result.map(settings =>
      {
        auth: settings.auth,
        lastUpdated: settings.lastUpdated,
        user: settings.user,
      }
    )
  ->Future.value;
};

let storageKey = "settings";

let getSettings = () => {
  ReactNative.AsyncStorage.getItem(storageKey)
  ->FutureJs.fromPromise(error => {
      // @todo error
      Js.log2("ReasonablePhotos: useSettings: ", error);
      "Unable to access settings from device";
    })
  ->Future.flatMapOk(res => {
      res
      ->Js.Null.toOption
      ->Option.map(jsonString =>
          try(jsonString->Json.parseOrRaise->decodeJsonSettings) {
          | Json.ParseError(_) =>
            Future.value(Result.Error("Unable to parse json settings"))
          }
        )
      ->Option.getWithDefault(Future.value(Ok(defaultSettings)))
    })
  ->Future.map(
      fun
      | Ok(settings) => settings
      | Error(err) => {
          Js.log(err);
          defaultSettings;
        },
    );
};

let useSettings = () => {
  let (settings, set) = React.useState(() => defaultSettings);
  React.useEffect1(
    () => {
      getSettings()->Future.tap(settings => set(_ => settings))->ignore;
      None;
    },
    [|set|] // TODO: why watching a function here- instead of a variable.?
  );
  React.useEffect1(
    () => {
      if (settings !== defaultSettings) {
        settings
        ->Js.Json.stringifyAny
        ->Option.map(stringifiedSettings =>
            ReactNative.AsyncStorage.setItem(storageKey, stringifiedSettings)
          )
        ->ignore;
        // if (ReactNative.Global.__DEV__) {
        //   Js.log2(
        //     "Settings",
        //     settings->Obj.magic->Js.Json.stringifyWithSpace(2),
        //   );
        // };
      };
      None;
    },
    [|settings|],
  );
  (settings, set);
};

type setSettingsT = t => t;
let defaultContext: (t, setSettingsT => unit) = (defaultSettings, _ => ());
let context = React.createContext(defaultContext);

module ContextProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(context);
};
