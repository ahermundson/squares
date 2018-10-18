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
               Js.log(response);
               <h1> {str("We have data people")} </h1>;
             }
         }
    </GetAllGamesQuery>,
};