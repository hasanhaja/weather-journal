// This may not be the best way to do it, but it's temporary so I can push this to GitHub.
let apiKey = Secret.apiKey;

let city = "London";
let unit = "metric";

type city = {
  name: string,
  country: string,
};

type weather = {
  temp: float,
  feels_like: float,
};

type weatherData = {main: weather};

type data = {
  list: array(weatherData),
  city,
};

let decodeCity = json => {
  Json.Decode.{
    name: json |> field("name", string),
    country: json |> field("country", string),
  };
};

let decodeWeather = json => {
  Json.Decode.{
    temp: json |> field("temp", float),
    feels_like: json |> field("feels_like", float),
  };
};

let decodeWeatherData = json => {
  Json.Decode.{main: json |> field("main", decodeWeather)};
};

let decodeData = json => {
  Json.Decode.{
    list: json |> field("list", array(decodeWeatherData)),
    city: json |> field("city", decodeCity),
  };
};

let url =
  "https://api.openweathermap.org/data/2.5/forecast?q="
  ++ city
  ++ "&APPID="
  ++ apiKey
  ++ "&units="
  ++ unit;

let fetchWeather = url => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => json |> decodeData |> resolve)
  );
};
