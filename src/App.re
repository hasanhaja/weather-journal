type state =
  | Loading
  | ErrorFetchingWeather
  | Loaded(Data.data);

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => Loading);

  React.useEffect0(() => {
    Data.fetchWeather(Data.url)
    |> Js.Promise.then_(data => {
         setState(_ => Loaded(data));
         Js.Promise.resolve();
       })
    |> ignore;

    None;
  });

  <div>
    {switch (state) {
     | Loading => "Loading..." |> React.string
     | ErrorFetchingWeather => "An error has occurred!" |> React.string
     | Loaded(data) =>
       let city = data.city.name;
       let temp = data.list[0].main.temp;
       "The temperature in "
       ++ city
       ++ " is "
       ++ Belt.Float.toString(temp)
       ++ " degrees Celcius."
       |> React.string;
     }}
  </div>;
};
