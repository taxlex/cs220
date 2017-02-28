int lastWon(int round, rps *myhist,rps *opphist){
	//1 = i won last, 2 = opp won last, 3 we tied last
	if(myhist[round-1] == Rock && opphist[round-1] == Scissors) return 1;
	else if(myhist[round-1] == Rock && opphist[round-1] == Paper) return 2;
	else if(myhist[round-1] == Rock && opphist[round-1] == Rock) return 3;
	
	else if(myhist[round-1] == Paper && opphist[round-1] == Scissors) return 2;
	else if(myhist[round-1] == Paper && opphist[round-1] == Paper) return 3;
	else if(myhist[round-1] == Paper && opphist[round-1] == Rock) return 1;
	
	else if(myhist[round-1] == Scissors && opphist[round-1] == Scissors) return 3;
	else if(myhist[round-1] == Scissors && opphist[round-1] == Paper) return 1;
	else if(myhist[round-1] == Scissors && opphist[round-1] == Rock) return 2;
}
rps player_abenedi1(int round,rps *myhist,rps *opphist) {
	rps myPlay = Rock;
	int lastRound = lastWon(round,myhist,opphist);
	if(lastRound == 1){
		int risk = rand()%5;
		if(myhist[round-1] == Rock && risk >=2) myPlay = Rock;
		if(myhist[round-1] == Rock && risk < 2) myPlay = Scissors;
		else if(myhist[round-1] == Paper && risk >=2) myPlay = Paper;
		else if(myhist[round-1] == Paper && risk < 2) myPlay = Rock;
		else if(myhist[round-1] == Scissors && risk >=2) myPlay = Scissors;
		else myPlay = Paper;
	}
	//lost last round
	else if (lastRound == 2){
		if(opphist[round-1]==Rock) myPlay= Paper;
		else if(opphist[round-1]==Paper) myPlay = Scissors;
		else myPlay = Rock;
	}
	//tied last round
	else{
		if(myhist[round-1] == Rock) myPlay = Paper;
		else if(myhist[round-1] == Paper) myPlay = Scissors;
		else myPlay = Rock;
	}
	return myPlay;
}

register_player(player_abenedi1,"abenedi1");
