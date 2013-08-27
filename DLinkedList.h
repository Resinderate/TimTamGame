/*
	DLinkedList.h
	Written by Ronan Murphy
	21/04/2013

	A Doubly Linked List Datastructure made up of nodes, and used together in a List.
*/

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

//forward class definitions needed because we use
//classes before they are defined
template <class Datatype> class DListNode;
template <class Datatype> class DLinkedList;
template <class Datatype> class DListIterator;


//----------------------------------------------------
//Name:           DListNode
//Description:    This is the node, of which each element is made up of.
//----------------------------------------------------


template<class Datatype>
class DListNode
{
private:
	// data in node
	Datatype m_data;
	// pointer to next node
	DListNode<Datatype>* m_next;
	//pointer to previous node
	DListNode<Datatype>* m_prev;
public:

	//----------------------------------------------------
	//Name:           Getters & Setters
	//Description:    Simple methods for getting and setting the private values in the node.
	//----------------------------------------------------
	// Order(c)
	//DATA
	Datatype& GetData()
	{
		return m_data;
	}

	void SetData(Datatype& p_data)
	{
		m_data = p_data;
	}

	//NEXT
	DListNode<Datatype>* GetNext()
	{
		return m_next;
	}

	void SetNext(DListNode<Datatype>* p_next)
	{
		m_next = p_next;
	}

	//PREV
	DListNode<Datatype>* GetPrev()
	{
		return m_prev;
	}

	void SetPrev(DListNode<Datatype>* p_prev)
	{
		m_prev = p_prev;
	}

	//----------------------------------------------------
	//Name:				DListNode
	//Description:		Constructor for the node.
	//Args:				None
	//----------------------------------------------------
	// Order(c)
	DListNode()
	{
		m_next = 0;
		m_prev = 0;
	}

	//----------------------------------------------------
	//Name:				InsertAfter
	//Description:		Inserts a new node after this one, with the given data inside.
	//Args:				p_data, the data to create a new node with, and insert
	//Return:			None
	//----------------------------------------------------
	//  Order(c)
	void InsertAfter(Datatype p_data)
	{
		// create new node
		DListNode<Datatype>* newnode = new DListNode<Datatype>;

		newnode->SetData(p_data);


		//update newnodes pointers
		newnode->SetNext(m_next);
		newnode->SetPrev(this);

		//update following nodes pointer
		if(m_next != 0)
			m_next->SetPrev(newnode);

		//update previous node pointer (this node)
		m_next = newnode;
	}
};

//----------------------------------------------------
//Name:           DLinkedList
//Description:    This is the list which hold all the nodes together
//----------------------------------------------------

template<class Datatype>
class DLinkedList
{
private:
	DListNode<Datatype>*m_head;
	DListNode<Datatype>*m_tail;
	int m_count;
public:

	//----------------------------------------------------
	//Name:           Getters & Setters
	//Description:    Simple methods for getting and setting the private values in the node.
	//----------------------------------------------------
	// Order(c)
	//HEAD
	DListNode<Datatype>* GetHead()
	{
		return m_head;
	}

	void SetHead(DListNode<Datatype>* p_head)
	{
		m_head = p_head;
	}

	//TAIL
	DListNode<Datatype>* GetTail()
	{
		return m_tail;
	}

	void SetTail(DListNode<Datatype>* p_tail)
	{
		m_tail = p_tail;
	}

	//COUNT
	int GetCount()
	{
		return m_count;
	}

	void SetCount(int p_count)
	{
		m_count = p_count;

		if(m_count < 0)
			m_count = 0;
	}

	//----------------------------------------------------
	//Name:				DLinkedList
	//Description:		Consrtuctor for the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	DLinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}

	//----------------------------------------------------
	//Name:				~DLinkedList
	//Description:		Desctructor for the list
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	~DLinkedList()
	{
		//Temporary node pointer
		DListNode<Datatype>* itr = m_head;
		DListNode<Datatype>* next = 0;

		while(itr != 0)
		{
			//save the pointer to next node 
			next = itr->GetNext();

			//delete the current node
			delete itr;

			//make the next node the current node
			itr = next;
		}
	}

	//----------------------------------------------------
	//Name:				Append
	//Description:		Appends a new node onto the end of the list.
	//Args:				p_data, the data to put into the new node.
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void Append(Datatype p_data)
	{
		//check if list is empty
		if(m_head == 0)
		{
			//the list is empty
			//creat a new node and make the head and tail point there

			m_head=m_tail=new DListNode<Datatype>;
			m_head->SetData(p_data);
		}
		else
		{
			//insert new node after the tail and update the tail
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->GetNext();
		}
		//m_count++
		SetCount(GetCount()+1);
	}

	//----------------------------------------------------
	//Name:				Prepend
	//Description:		Adds a new node at the start of the list.
	//Args:				p_data, the data to put into the new node.
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void Prepend(Datatype p_data)
	{
		//create a new node
		DListNode<Datatype>* newnode = new DListNode<Datatype>;
		newnode->SetData(p_data);
		newnode->SetNext(m_head);

		m_head->SetPrev(newnode);


		//set the head node and the tail node if necessary
		m_head = newnode;
		if(m_tail == 0)
		{
			m_tail = m_head;
		}
		//m_count++
		SetCount(GetCount()+1);
	}

	//----------------------------------------------------
	//Name:				RemoveHead
	//Description:		Removes the first element of the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void RemoveHead()
	{
		DListNode<Datatype>* node = 0;

		if (m_head != 0)
		{
			//make the node point to the next node
			node = m_head->GetNext();

			//now delete the head and make head point to node
			delete m_head;
			m_head = node;
			node = 0;
			if(m_head !=0)
				m_head->SetPrev(node);


			//if the head is null , we have just deleted the only
			//element in the list, set the tail to 0

			if(m_head == 0)
			{
				m_tail = 0;
			}

			//m_count--
			SetCount(GetCount()-1);
		}
	}

	//----------------------------------------------------
	//Name:				RemoveTail
	//Description:		Removes the last element of the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void RemoveTail()
	{
		DListNode<Datatype>*node = m_tail;

		//Check if the list is empty, and if so, do nothing.
		if(m_head != 0)
		{
			//if only one element
			if(m_head == m_tail)
			{
				delete m_head;
				m_head = m_tail = 0;
			}
			//There is more than one element
			else 
			{
				node = m_tail;

				//make the tail point to the node before the last node
				//and delete the old tail

				m_tail = node->GetPrev();
				delete node;				
				m_tail->SetNext(0);
			}
			SetCount(GetCount()-1);
		}
	}

	//----------------------------------------------------
	//Name:				GetIterator
	//Description:		Get an iterator for the current list, pointing to the start of the list
	//Args:				None
	//Return:			DListIterator<Datatype>
	//----------------------------------------------------
	// Order(c)

	DListIterator<Datatype> GetIterator()
	{
		return DListIterator<Datatype>(this, m_head);
	}


	//---------------------------------
	//Name:         Insert
	//Description:  insert new data after the given iterator or append if the iterator is not valid.
	//Args:			p_iterator, iterator to insert after
	//              p_data, data to insert
	//Return:		None
	//-------------------------------------------------------
	// Order(c)

	void Insert(DListIterator<Datatype>& p_iterator, Datatype p_data)
	{
		//If the iterator doesnt belong to this list
		if(p_iterator.GetList() != this)
		  return;

		if(p_iterator.GetNode() !=0)
		{
			//the iterator is valid, insert the node
			p_iterator.GetNode()->InsertAfter(p_data);

			//if the iterator is the tail node
			//then update the tail

			if(p_iterator.GetNode() == m_tail)
			{
				m_tail = p_iterator.GetNode()->GetNext();
			}
			m_count++;
		}
		else
		{
			//iterator not valid, append onto end of list
			Append(p_data);
		}
	}

	//----------------------------------------------------
	//Name:				Remove
	//Description:		Remove the element, pointed to by the given iterator.
	//Args:				p_iterator, itrator pointing to the element you want to remove
	//Return:			None
	//----------------------------------------------------
	// Order(c)

	void Remove(DListIterator<Datatype>& p_iterator)
	{
		DListNode<Datatype>* node = m_head;

		//check if the iterator doesn't belong to this list, then there is something wrong.
		if(p_iterator.GetList() != this)
			return;

		//if the node is not valid, then nothing to do.
		if(p_iterator.GetNode() == 0)
		{
			return;
		}

		//Not sure if a possibilty. You shouldn't be able to get a pointer to something in the list, if it is empty. Just in case.
		if(m_count == 0)
		{
			return;
		}

		//If it's the head
		if(p_iterator.GetNode() == m_head)
		{
			p_iterator.Forth();
			RemoveHead();
		}
		//If it's the tail
		else if(p_iterator.GetNode() == m_tail)
		{
			p_iterator.Back();
			RemoveTail();
		}
		//Somewhere in the middle
		else
		{
			//Set the node before's m_next, to point to the one after the iterator.
			p_iterator.GetNode()->GetPrev()->SetNext(p_iterator.GetNode()->GetNext());

			//Set the node after's m_prev, to point to the one before.
			p_iterator.GetNode()->GetNext()->SetPrev(p_iterator.GetNode()->GetPrev());

			DListNode<Datatype>* temp = p_iterator.GetNode();
			p_iterator.Forth();
			delete temp;
			SetCount(GetCount()-1);
		}
		
	}

	//----------------------------------------------------
	//Name:				SaveToDisk
	//Description:		Save the list to a file by the given name.
	//Args:				p_filename, the name of the file you want to save to.
	//Return:			bool, if the save was successful.
	//----------------------------------------------------
	// Order(n) - based on how much info you have to write.

	bool SaveToDisk(char* p_filename)
	{
		FILE* outfile = 0;
		DListNode<Datatype>* itr = m_head;
		outfile = fopen(p_filename, "wb");

		if(outfile  == 0)
			return false;

		fwrite(&m_count, sizeof(int), 1, outfile);

		while(itr!= 0)
		{
			fwrite(&(itr->GetData()), sizeof(Datatype), 1, outfile);
			itr= itr->GetNext();
		}

		fclose(outfile);
		return true;
	}

	//----------------------------------------------------
	//Name:				ReadFromDisk
	//Description:		Reads in from the given file and saves the contents into the list
	//Args:				p_filename, the file you want to read from.
	//Return:			bool, if it was successful.
	//----------------------------------------------------
	// Order(n) - based on how much info you have to read.

	bool ReadFromDisk(char* p_filename)
	{
		FILE* infile= 0;
		Datatype buffer;
		int count = 0;

		infile = fopen(p_filename, "rb" );

		if(infile == 0 )
			return false;

		fread(&count, sizeof(int), 1, infile);

		while(count != 0 )
		{
			fread(&buffer, sizeof(Datatype), 1, infile);
			Append(buffer);
			count--;
		}
		fclose(infile);
		//ERROR Here. No idea what is causing it.
		return true;
	}

};


			
//---------------------------------------------------
//Name:           DListIterator
//Description:    Iterator for a singly linked list
//---------------------------------------------------


template <class Datatype>
class DListIterator
{
private:
	DListNode <Datatype>* m_node;
	DLinkedList<Datatype>* m_list;
public:

	//----------------------------------------------------
	//Name:           Getters & Setters
	//Description:    Simple methods for getting and setting the private values in the node.
	//----------------------------------------------------
	// Order(c)

	//NODE
	DListNode<Datatype>* GetNode()
	{
		return m_node;
	}

	void SetNode(DListNode<Datatype>* p_node)
	{
		m_node = p_node;
	}

	//LIST - ONLY GETTER
	DLinkedList<Datatype>* GetList()
	{
		return m_list;
	}

	//----------------------------------------------------
	//Name:				DListIterator
	//Description:		Constructor for the iterator.
	//Args:				p_list, the list to be associated with the iterator
	//					p_node, the node for the iterator to point to innitially
	//Return:			None
	//----------------------------------------------------
	DListIterator(DLinkedList<Datatype>* p_list=0, 
		DListNode<Datatype>* p_node=0)
	{
		m_list = p_list;
		m_node = p_node;
	}

	//----------------------------------------------------
	//Name:				Start
	//Description:		Points the iterator to the first element in the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void Start()
	{
		if(m_list !=0)
		{
			m_node = m_list->GetHead();
		}
	}

	//----------------------------------------------------
	//Name:				End
	//Description:		Points the iterator to the last element in the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------.
	//Order(c)

	void End()
	{
		if(m_list != 0)
		{
			m_node = m_list->GetTail();
		}
	}

	//----------------------------------------------------
	//Name:				Forth
	//Description:		Makes the iterator step one element forward in the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	// Order(c)

	void Forth()
	{
		if(m_node != 0)
		{
			m_node = m_node->GetNext();
		}
	}

	//----------------------------------------------------
	//Name:				Back
	//Description:		Makes the iterator step one element backwards in the list.
	//Args:				None
	//Return:			None
	//----------------------------------------------------
	// Order(c)
	void Back()
	{
		if(m_node != 0)
		{
			m_node = m_node->GetPrev();
		}
	}

	//----------------------------------------------------
	//Name:				Item
	//Description:		Returns the item being stored in the node that the iterator is pointing to.
	//Args:				None
	//Return:			Datatpye&, the item being returned.
	//----------------------------------------------------
	// Order(c)

	Datatype& Item()
	{
		return m_node->GetData();
	}


	//----------------------------------------------------
	//Name:				Valid
	//Description:		Checking if the iterator is pointing to a valid location
	//Args:				None
	//Return:			bool, if the iterator is valid.
	//----------------------------------------------------
	// Order(c)

	bool Valid()
	{
		return(m_node != 0);
	}
};

#endif


