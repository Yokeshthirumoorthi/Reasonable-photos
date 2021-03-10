[@decco]
type t = {lastUpdated: float};

let defaultSettings = {lastUpdated: 0.};

let decodeJsonSettingsOrRaise = (json: Js.Json.t): t =>
  t_decode(json)->Belt.Result.getExn;

let decodeJsonSettings = (json: Js.Json.t): Future.t(Result.t(t, string)) => {
  (
    try(Ok(json->decodeJsonSettingsOrRaise)) {
    | _ => Error("Ooops! Something went wrong when loading settings")
    }
  )
  ->Result.map(settings => {lastUpdated: settings.lastUpdated})
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
          try(jsonString->Js.Json.parseExn->decodeJsonSettings) {
          | _ => Future.value(Result.Error("Unable to parse json settings"))
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
