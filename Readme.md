42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

Steps Followed to succed the project :
    Parsing Part 
        1 - Parse and store the enviroment variables
        2 - Read lines from the stdin and parse it
        3 - Make tokens from the readed lines



Parsing Function :
    Enviroment:
        ft_addnodeenv() -> Fucntion That Creates a Node Initialize it with its
            key value strings.
        ft_returnlastnodeenv() -> Function That Travers a linked liste 
            and return its  last variable  
        ft_initnodeenv() -> Function That Parse and split string into key value
            and store data in their correct places
        ft_freeenv() -> This Function Free the allocated space for 
            the Enviroment variables ( linked list )
        ft_envholder() -> This Function Strores The evn array 
            into a new one
        ft_freeenvholder() -> This Function Frees The env new holder
