[%bs.raw {|require('./App.css')|}];

open SharedTypes;
module GetGameSquares = [%graphql
  {|
    query getThoseGameSquares($id: ID!) {
        getGameSquares(id: $id) {
            x
            y
            isTaken
        }
    }
  |}
];

module GetGameSquareQuery = ReasonApollo.CreateQuery(GetGameSquares);

type row = Js.Array.t(square);
type board = Js.Array.t(row);
type state = {currentUserID: option(int)};
type action =
  | ClickSquare(square)
  | AddUser;

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.string;

let parseSquares = squares =>
  switch (squares) {
  | None => [||]
  | Some(squares) =>
    let filtered = squares |> Js.Array.filter(square => square##x == 0);
    Js.Array.sortInPlace(filtered);
  };

/* let createBoardRows = squares => {
     parseItems(squares)
     |> Js.Array.filter(square => square##x == 0)
     |> Array.to_list;
     ();
   }; */

let clicker = test => Js.log(test);
let make = (~selectedGame, _children) => {
  ...component,
  initialState: () => ({currentUserID: None}: state),
  reducer: (action: action, _state: state) =>
    switch (action) {
    | ClickSquare(_clickedSquare) =>
      ReasonReact.Update({currentUserID: Some(1)})
    | AddUser => ReasonReact.Update({currentUserID: Some(1)})
    },
  render: ({state, send}) =>
    switch (state.currentUserID) {
    | None =>
      Js.log(selectedGame);
      <button onClick=(_evt => send(AddUser))> {str("Test")} </button>;
    | Some(_userID) =>
      let gameQuery = GetGameSquares.make(~id="5bd4bed2dfe6d3b637be8662", ());
      <div className="App">
        <h1> {str("Squares")} </h1>
        <GetGameSquareQuery variables=gameQuery##variables>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => <h1> {str("Loading")} </h1>
                 | Error(error) =>
                   Js.log(error);
                   <h1> {str("Error")} </h1>;
                 | Data(response) =>
                   let gameSquares = response##getGameSquares;
                   let parsedSquares = parseSquares(gameSquares);
                   Js.log(parsedSquares);
                   <BoardRow row=parsedSquares click=clicker />;
                 }
             )
        </GetGameSquareQuery>
      </div>;
    },
};