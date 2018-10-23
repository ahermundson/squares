let str = ReasonReact.string;

module GetAllGames = [%graphql
  {|
    query getAllGames {
        allGames {
            _id
        }
    }
  |}
];

type t = {
  _id: string,
  firstQuarterHome: option(Js.null(int)),
  firstQuarterAway: option(Js.null(int)),
  secondQuarterHome: option(Js.null(int)),
  secondQuarterAway: option(Js.null(int)),
  thirdQuarterHome: option(Js.null(int)),
  thirdQuarterAway: option(Js.null(int)),
  fourthQuarterHome: option(Js.null(int)),
  fourthQuarterAway: option(Js.null(int)),
};

type games = array({. "_id": string});
/* module Decode = {
     let optionalField = (fieldName, decoder) =>
       Json.Decode.(optional(field(fieldName, decoder)));
     let optionalNullableField = (fieldName, decoder) =>
       Json.Decode.(optional(field(fieldName, nullable(decoder))));

     let game = json =>
       Json.Decode.{
         _id: optionalField("_id", string),
         firstQuarterHome: optionalNullableField("firstQuarterHome", int),
         firstQuarterAway: optionalNullableField("firstQuarterAway", int),
         secondQuarterHome: optionalNullableField("secondQuarterHome", int),
         secondQuarterAway: optionalNullableField("secondQuarterAway", int),
         thirdQuarterHome: optionalNullableField("thirdQuarterHome", int),
         thirdQuarterAway: optionalNullableField("thirdQuarterAway", int),
         fourthQuarterHome: optionalNullableField("fourthQuarterHome", int),
         fourthQuarterAway: optionalNullableField("fourthQuarterAway", int),
       };

     let games = json: list(game) => Json.Decode.list(game, json);
   }; */

module GetAllGamesQuery = ReasonApollo.CreateQuery(GetAllGames);

let component = ReasonReact.statelessComponent("Games");

let make = _children => {
  ...component,
  render: _self =>
    <GetAllGamesQuery>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <h1> {str("Loading")} </h1>
             | Error(_error) => <h1> {str("Error")} </h1>
             | Data(response) =>
               switch (response##allGames) {
               | None => <h1> {str("No games")} </h1>
               | Some(games) =>
                 games
                 |> Js.Array.map(game => <Game key=game##_id game />)
                 |> ReasonReact.array
               }
             }
         }
    </GetAllGamesQuery>,
};