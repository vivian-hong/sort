/*
 * A replacement for (integer) arrays that lets you say dynamically
 * how big the array should be.
 *
 * Mark A. Sheldon, Tufts University
 * Spring 2013
 *
 */

class IntVector
{
public:
        IntVector();

        /*
         * A constructor with an initial size is optional.
         */
        IntVector(int initialSize);

        /*
         * You have two choices with the copy constructor and
         * assignment operator:
         *      - implement them correctly, or
         *      - make them private
         *
         * Making them private means that clients can't use them,
         * i. e., they won't be able to pass or return them by value
         * or assign them.
         *
         * Copying 100,000 element arrays is not something you want
         * to do lightly!
         */
        IntVector(const IntVector &source);
        IntVector &operator=(const IntVector &rhs);

        ~IntVector();

        /*
         * Makes the vector have a size and capacity of 0 and 
         * recycles heap-allocated storage.
         * The client may continue to use the IntVector after
         * calling destroy, e. g., they could add elements to it.
         */
        void destroy();

        /*
         * Return integer value at given index.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int get(int index) const;

        /*
         * Set array element at given index to newVal.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        void set(int index, int newVal);

        /*
         * Return reference to array slot at given index.
         * This permits subscripted access to vector as 
         * L-value and/or R-value.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int  &operator[](int index) const;

        /* Add newVal to end of vector, increasing current size by one. */
        void  add(int newVal);

        /* Return current size of vector. */
        int size() const;

        /* Return current capacity of vector */
        int capacity() const;

private:
        int *vector;
        int vector_size;
        int vector_capacity;
        void expand();
        void copy (int *copy_vector) const;
};
