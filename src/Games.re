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
  _id: option(string),
  firstQuarterHome: option(Js.null(int)),
  firstQuarterAway: option(Js.null(int)),
  secondQuarterHome: option(Js.null(int)),
  secondQuarterAway: option(Js.null(int)),
  thirdQuarterHome: option(Js.null(int)),
  thirdQuarterAway: option(Js.null(int)),
  fourthQuarterHome: option(Js.null(int)),
  fourthQuarterAway: option(Js.null(int)),
};

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
               Js.log(response##allGames);
               let gamesList =
                 response##allGames
                 |> Array.map(game =>
                      switch (game) {
                      | Some(game) =>
                        let id = Some(game##_id);
                        ();
                      }
                    );

               ReasonReact.arrayToElement(gamesList);
             }
         }
    </GetAllGamesQuery>,
};