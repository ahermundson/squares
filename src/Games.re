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

type gameType = {_id: string};

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
                      <h1 key=game##_id> {str(game##_id)} </h1>
                    );

               ReasonReact.arrayToElement(gamesList);
             }
         }
    </GetAllGamesQuery>,
};