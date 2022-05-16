chessBoard->board[file][rank]->counter = 0;

void MoveRandomBlack(Board *b)
{
	srand(time(NULL)); 
	int a = rand() % 8; 
	int e = rand() % 8; 
	int c = rand() % 8; 
	int d = rand() % 8; 
	int count = 0;
	while (1)
	{	
		a = rand() % 8; //Select a Random file for initial move
		e = rand() % 8; //Select a Random rank for initial move

		if(b->board[a][e]->color == BLACK)
		{
			for(count = 0; count <= 200; count++) 
			//Repeat the loop 200 times to find a valid move
			//200 is chosen randomly in order to avoid pieces which do not have any valid moves
			//If there are no valid moves in 200 tries, the loop breaks
			{
				c = rand() % 8; //Select a Random file for final move
				d = rand() % 8; //Select a Random rank for final move
				if (IsValid(a,e,c,d,b))
				{
					Move(a,e,c,d,b);
					return;
				}
			}
		}
	}
}

void MoveRandomWhite(Board *b)
{
	srand(time(NULL)); 
	int a = rand() % 8; 
	int e = rand() % 8; 
	int c = rand() % 8; 
	int d = rand() % 8; 
	int count = 0;
	while (1)
	{	
		a = rand() % 8; //Select a Random file for initial move
		e = rand() % 8; //Select a Random rank for initial move

		if(b->board[a][e]->color == WHITE)
		{
			for(count = 0; count <= 200; count++) 
			//Repeat the loop 200 times to find a valid move
			//200 is chosen randomly in order to avoid pieces which do not have any valid moves
			//If there are no valid moves in 200 tries, the loop breaks
			{
				c = rand() % 8; //Select a Random file for final move
				d = rand() % 8; //Select a Random rank for final move
				if (IsValid(a,e,c,d,b))
				{
					Move(a,e,c,d,b);
					return;
				}
			}
		}
	}
}


LL *getValidMovesKing(int f,int r, Board *b){
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;
		
	//Castling using White Rook on the Right Side
	if (b->board[7][0]->piece == ROOK && b->board[7][0]->color == WHITE && b->board[f][r]->counter == 0 && f == 4 && r == 0 && b->board[f][r]->color == WHITE && b->board[f+1][r]->piece == EMPTY && b->board[f+2][r]->piece == EMPTY && b->board[6][0]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 0;
		curr->f1 = 6;
		Append(out, curr);
	} 

	//Castling using White Rook on the Left Side
	if (b->board[0][0]->piece == ROOK && b->board[0][0]->color == WHITE && b->board[f][r]->counter == 0 && f == 4 && r == 0 && b->board[f][r]->color == WHITE && b->board[f-1][r]->piece == EMPTY && b->board[f-2][r]->piece == EMPTY && b->board[f-3][r]->piece == EMPTY  && b->board[2][0]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 0;
		curr->f1 = 2;
		Append(out, curr);
	}	
	
	//Castling using Black Rook on the Right Side
	if (b->board[7][7]->piece == ROOK && b->board[7][7]->color == BLACK && b->board[f][r]->counter == 0 && f == 4 && r == 7 && b->board[f][r]->color == BLACK && b->board[f+1][r]->piece == EMPTY && b->board[f+2][r]->piece == EMPTY  && b->board[6][7]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 7;
		curr->f1 = 6;
		Append(out, curr);
	}

	//Castling using Black Rook on the Left Side
	if (b->board[0][7]->piece == ROOK && b->board[0][7]->color == BLACK && b->board[f][r]->counter == 0 && f == 4 && r == 7 && b->board[f][r]->color == BLACK && b->board[f-1][r]->piece == EMPTY && b->board[f-2][r]->piece == EMPTY && b->board[f-3][r]->piece == EMPTY  && b->board[2][7]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 7; 
		curr->f1 = 2;
		Append(out, curr);
	}

	//Check 1 space above
	if (r+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space below
		
	if (r-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the left

	if (f-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f-1][r]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the right
	
	if (f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the Upper Right
	
	if (r+1 <= 7 && f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space to the Upper Left
	
	if (r+1 <= 7 && f-1 >=0)
	{
		if (b->board[f][r]->color != b->board[f-1][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space to the Lower Right
	
	if (r-1 >= 0 && f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the Lower Left
	
	if (r-1 >= 0 && f-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f-1][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	return out;
}

void Castling(int f0, int r0, int f1, int r1, Board *b)
{
	if (f1 == 6 && r1 == 0 && f0 == 4 && r0 == 0)
	{
		Piece *x = b->board[7][0];
		
		b->board[7][0] = b->board[5][0];
		b->board[5][0] = x;
		x->isKCastled = true;

	}

	if (f1 == 2 && r1 == 0 && f0 == 4 && r0 == 0)
	{
		Piece *x = b->board[0][0];
		
		b->board[0][0] = b->board[3][0];
		b->board[3][0] = x;
		x->isQCastled = true;
	}

	if (f1 == 6 && r1 == 7 && f0 == 4 && r0 == 7)
	{
		Piece *x = b->board[7][7];
		
		b->board[7][7] = b->board[5][7];
		b->board[5][7] = x;
		x->isKCastled = true;
	}

	if (f1 == 2 && r1 == 7 && f0 == 4 && r0 == 7)
	{
		Piece *x = b->board[0][7];
		
		b->board[0][7] = b->board[3][7];
		b->board[3][7] = x;
		x->isQCastled = true;
	}

}

