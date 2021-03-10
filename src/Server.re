external promiseErrorToJsObj: Js.Promise.error => Js.t('a) = "%identity";
/* Using a custom error */
exception Oh_no(string);

module type Interface = {
  let post: (string, Js.t('b)) => Js.Promise.t(Js.Json.t);
};

module Make: Interface = {
  let post = (apipath, payload) =>
    Axios.postDatac(
      "http://144.126.210.159:3000/api" ++ apipath,
      payload,
      Axios.makeConfig(
        ~withCredentials=false,
        ~headers=Axios.Headers.fromObj({"content-type": "application/json"}),
        (),
      ),
    )
    |> Js.Promise.then_(resp => resp##data->Js.Promise.resolve)
    |> Js.Promise.catch(error => {
         let error = error->promiseErrorToJsObj;
         Js.log(error);
         Js.Promise.reject(Oh_no("Request failed: " ++ error##response));
       });
};
