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
     | Loaded(data) => "YAY! London's weather data received!" |> React.string
     }}
  </div>;
};
