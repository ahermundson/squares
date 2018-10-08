let component = ReasonReact.statelessComponent("BoardRow");
let str = ReasonReact.string;

type square = {
    id: int,
    isTaken: bool,
    x: int,
    y: int
  };

let make = (~row, _children) => {
    ...component,
    render: _self => {
        row
        |> List.map((square: square) => {
            Js.log(square.x);
            <div key={string_of_int(square.id)}>
                <h1>{str("X " ++ string_of_int(square.x))}</h1>
                <h1>{str("Y " ++ string_of_int(square.y))}</h1>
                
            </div>
            
        }
        )
        |> Array.of_list
        |> ReasonReact.array
    }
}