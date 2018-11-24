let component = ReasonReact.statelessComponent("Square");
let str = ReasonReact.string;
open SharedTypes;

module MarkSquare = [%graphql
  {|
  mutation markSquare($id: ID!) {
      markSquare(id: $id) {
          isTaken
      }
  }
|}
];

module MarkSquareMutation = ReasonApollo.CreateMutation(MarkSquare);

let make = (~square: square, _children) => {
  ...component,
  render: _self =>
    <MarkSquareMutation>
      ...{
           (mutation, _) => {
             let updatedSquare = MarkSquare.make(~id=square##_id, ());
             square##isTaken ?
               switch (square##takenByUser) {
               | None =>
                 <div className="square"> <h1> {str("Taken")} </h1> </div>
               | Some(user) =>
                 <div className="square">
                   <h1> {str(user##first_name)} </h1>
                 </div>
               } :
               <div
                 className="square"
                 key={string_of_int(square##x)}
                 onClick={
                   _mouseEvent =>
                     mutation(~variables=updatedSquare##variables, ())
                     |> ignore
                 }>
                 <h1> {str("X " ++ string_of_int(square##x))} </h1>
                 <h1> {str("Y " ++ string_of_int(square##y))} </h1>
               </div>;
           }
         }
    </MarkSquareMutation>,
};