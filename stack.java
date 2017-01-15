import java.util.Iterator;

/**
 *
 * @author RAVEESH
 */
public class stack<Item> implements Iterable<Item>{

    Node first;
    
    private class Node{
        Item item;
        Node next;
    }
    
   
    
    @Override
    public Iterator<Item> iterator() {
        return new ListIterator();
    }
    
    private class ListIterator implements Iterator<Item>{

        Node current=first;
        
        @Override
        public boolean hasNext() {
            return (current!=null);
        }

        @Override
        public Item next() {
            Item temp=current.item;
            current=current.next;
            return temp;
        }
        
    }
    
    public stack(){
        first=null;
    }
    
    void push(Item item){
        Node temp = new Node();
        temp.item=item;
        temp.next=first;
        first=temp;
    }
    
    boolean isEmpty(){
        if(first!=null)
            return false;
        else
            return true;
    }
    
    Item top() throws Exception{
        if(!isEmpty())
            return first.item;
        else
            throw new Exception("Stack Underflow");
    }
    
    void pop() throws Exception{
        if(!isEmpty())
            first=first.next;
        else
            throw new Exception("Stack Underflow");
    }
            
    public static void main(String[] args) {
        stack<Integer> s = new stack<Integer>();
        s.push(1);
        s.push(2);
        s.push(3);
        s.push(4);
        System.out.println("Iterating stack: ");
        for(int item: s){
            System.out.println(item);
        }
        try{
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        s.pop(); // stack empty here
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}
