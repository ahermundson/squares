[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type row = list(Square.square);
type board = list(row);

let makeRow = (i, id) =>
  Belt.List.makeBy(10, (j: int) =>
    ({isTaken: false, id: id + j, x: i, y: j}: Square.square)
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

type state = {board};

type action =
  | ClickSquare(Square.square);

let component = ReasonReact.reducerComponent("App");

let test = (square: Square.square): unit => Js.log(square);

let str = ReasonReact.string;

let make = _children => {
  ...component,
  initialState: () => ({board: board}: state),
  reducer: (action: action, state: state) =>
    switch (action) {
    | ClickSquare(clickedSquare) =>
      Js.log(state.board);
      ReasonReact.Update({
        board:
          List.map(
            row =>
              List.map(
                (square: Square.square) =>
                  square.id == clickedSquare.id ?
                    {...square, isTaken: true} : square,
                row,
              ),
            state.board,
          ),
      });
    },
  render: self =>
    <div className="App">
      <h1> {str("Squares")} </h1>
      {
        board
        |> List.mapi((id: int, row) =>
             <BoardRow
               key={string_of_int(id)}
               row
               click={x => self.send(ClickSquare(x))}
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};