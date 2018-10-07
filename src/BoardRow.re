let component = ReasonReact.statelessComponent("BoardRow");

let make = (~row, _children) => {
    ...component,
    render: _self => {
        row
        |> Array.map(square => 
        <div key={string_of_int(square.id)}>
            <h1>{str("X " ++ string_of_int(square.x))}</h1>
            <h1>{str("Y " ++ string_of_int(square.y))}</h1>
            
        </div>
        )
        |> ReasonReact.array
    }
}