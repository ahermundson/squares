let str = ReasonReact.string;

module GetAllGames = [%graphql
  {|
    query getAllGames {
        allGames {
            _id
            boardId
            homeTeam {
              teamName
            }
        }
    }
  |}
];

module GetAllGamesQuery = ReasonApollo.CreateQuery(GetAllGames);

let component = ReasonReact.statelessComponent("Games");

let make = (~selectGame, _children) => {
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
                 |> Js.Array.map(game =>
                      <Game
                        key=game##_id
                        game
                        selectGame=(() => selectGame(game##boardId))
                      />
                    )
                 |> ReasonReact.array
               }
             }
         }
    </GetAllGamesQuery>,
};