public class Library {
    public Book[] books;
    public String address;
    public static int maxBooks = 100;
    public static String openingHours = "Libraries are open daily from 9am to 5pm.";
    public int numBooks = 0;
    public Library() {
        books = new Book[maxBooks];
    }
    public Library(String name) {
        this.address = name;
        books = new Book[maxBooks];
    }
    public void addBook(Book book) {
        this.books[numBooks] = book;
        numBooks++;
    }
    public static void printOpeningHours(){
        System.out.println(openingHours);
    }
    public void printAddress(){
        System.out.println(address);
    }
    public void borrowBook(String bookName) {
        for (int i = 0; i < numBooks; i++) {
            if(books[i].title.equals(bookName)){
                if (books[i].isBorrowed()){
                    System.out.println("Sorry, this book is already borrowed.");
                }else{
                    books[i].borrowed = true;
                    System.out.println("You successfully borrowed "+books[i].title);
                }
                return;
            }
        }
        System.out.println("Sorry, this book is not in our catalog.");
    }
    public void returnBook(String bookName) {
        for (int i = 0; i < numBooks; i++) {
            if(books[i].title.equals(bookName)){
                books[i].borrowed = false;
                System.out.println("You successfully returned "+books[i].title);
            }
        }
    }
    public void printAvailableBooks(){
        int flag = 0;
        for (int i = 0; i < numBooks; i++) {
            if(books[i].borrowed == false){
                System.out.println(books[i].title);
                flag++;
            }
        }
        if(flag == 0){
            System.out.println("No book in catalog");
        }
    }
    // Add the missing implementation to this class
    public static void main(String[] args) {
        // Create two libraries
        Library firstLibrary = new Library("10 Main St.");
        Library secondLibrary = new Library("228 Liberty St.");
        // Add four books to the first library
        firstLibrary.addBook(new Book("The Da Vinci Code"));
        firstLibrary.addBook(new Book("Le Petit Prince"));
        firstLibrary.addBook(new Book("A Tale of Two Cities"));
        firstLibrary.addBook(new Book("The Lord of the Rings"));
        // Print opening hours and the addresses
        System.out.println("Library hours:");
        printOpeningHours();
        System.out.println();
        System.out.println("Library addresses:");
        firstLibrary.printAddress();
        secondLibrary.printAddress();
        System.out.println();
        // Try to borrow The Lords of the Rings from both libraries
        System.out.println("Borrowing The Lord of the Rings:");
        firstLibrary.borrowBook("The Lord of the Rings");
        firstLibrary.borrowBook("The Lord of the Rings");
        secondLibrary.borrowBook("The Lord of the Rings");
        System.out.println();
        // Print the titles of all available books from both libraries
        System.out.println("Books available in the first library:");
        firstLibrary.printAvailableBooks();
        System.out.println();
        System.out.println("Books available in the second library:");
        secondLibrary.printAvailableBooks();
        System.out.println();
        // Return The Lords of the Rings to the first library
        System.out.println("Returning The Lord of the Rings:");
        firstLibrary.returnBook("The Lord of the Rings");
        System.out.println();
        // Print the titles of available from the first library
        System.out.println("Books available in the first library:");
        firstLibrary.printAvailableBooks();
    }
}