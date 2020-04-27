Util.requireCSS("./index.css");

let url = Data.url;

Js.log("The url is " ++ url);

Data.fetchWeather(url)
|> Js.Promise.then_(data => Js.log(data) |> Js.Promise.resolve);

ReactDOMRe.renderToElementWithId(<App />, "root");
