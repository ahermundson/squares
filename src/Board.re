[%bs.raw {|require('./App.css')|}];

open SharedTypes;
module GetGameSquares = [%graphql
  {|
    query getThoseGameSquares($id: ID!) {
        getGameSquares(id: $id) {
            x
            y
            isTaken
            takenByUser {
              _id
            }
        }
    }
  |}
];

module GetGameSquareQuery = ReasonApollo.CreateQuery(GetGameSquares);

type row = list(square);
type board = list(row);
type state = {currentUserID: option(int)};
type action =
  | ClickSquare(square)
  | AddUser;

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.string;

let createBoardRows = squares =>
  squares |> Js.Array.filter(square => square##x == 0) |> Array.to_list;

let updateBoard =
    (board: board, _clickedSquare: square, _currentUserID: option(int)) =>
  board
  |> List.map(row => row |> List.map((square: square) => Js.log(square)));

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
                   switch (response##getGameSquares) {
                   | None => <h1> {str("None")} </h1>
                   | Some(squares) =>
                     <BoardRow row={createBoardRows(squares)} />
                   }
                 }
             )
        </GetGameSquareQuery>
      </div>;
    },
};