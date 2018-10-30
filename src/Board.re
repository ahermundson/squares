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
type user = {
  name: string,
  id: int,
};

let makeRow = (i, id) =>
  Belt.List.makeBy(10, (j: int) =>
    ({isTaken: false, x: i, y: j, takenByUserID: None}: square)
  );

let board: board = [
  makeRow(0, 0),
  makeRow(1, 10),
  makeRow(2, 20),
  makeRow(3, 30),
  makeRow(4, 40),
  makeRow(5, 50),
  makeRow(6, 60),
  makeRow(7, 70),
  makeRow(8, 80),
  makeRow(9, 90),
];

type state = {
  board,
  currentUserID: option(int),
};

type action =
  | ClickSquare(square)
  | AddUser;

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.string;

let createBoardRows = (squares: GetGameSquares.t) =>
  switch (squares##getGameSquares) {
  | None => Js.log("None")
  | Some(squares) =>
    let zero =
      squares
      |> Js.Array.map(square =>
           {
             x: square.x,
             y: square.y,
             isTaken: square.isTaken,
             takenByUserID: square.takenByUserID,
           }
         )
      |> Js.Array.filter(newSquare => newSquare.x == 0);
    ();
  };

let updateBoard =
    (board: board, clickedSquare: square, currentUserID: option(int)) =>
  board
  |> List.map(row =>
       row
       |> List.map((square: square) =>
            square.id == clickedSquare.id ?
              {...square, isTaken: true, takenByUserID: currentUserID} :
              square
          )
     );

let make = (~selectedGame, _children) => {
  ...component,
  initialState: () => ({board, currentUserID: None}: state),
  reducer: (action: action, state: state) =>
    switch (action) {
    | ClickSquare(clickedSquare) =>
      ReasonReact.Update({
        ...state,
        board: updateBoard(state.board, clickedSquare, state.currentUserID),
      })
    | AddUser => ReasonReact.Update({...state, currentUserID: Some(1)})
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
                   createBoardRows(response);
                   <h1> {str("We have data")} </h1>;
                 }
             )
        </GetGameSquareQuery>
      </div>;
    },
};