#include "source.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define FRAME_RATE 60 
#define SPEED 5
#define FALLDOWN 5 
#define PIPE_WIDTH 80
int main()
{
    std::vector<Vector2> top_pillar_positions;
    std::vector<Vector2> bottom_pillar_positions;

    int randomGape = 0;
    int x_cordinatGape = 20;
     int frame_counter = 0;
    bool is_fliped = false;
    int temp_speed = SPEED;
    bool game_start = false;
    bool game_over = false;
    int wall_gap;
    int total_piller_height;
    int number_of_piller;
    int Score = 0;
    std::string score = std::to_string(Score);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GAME");
    SetTargetFPS(FRAME_RATE);
    Images *data = new Images();

    // Bird 

    Texture2D bird = LoadTextureFromImage(data->bird);
    UnloadImage(data->bird);
    Vector2 bird_position = { SCREEN_WIDTH/2 - bird.width, SCREEN_HEIGHT/2  - bird.height };
    Rectangle print_bird = { 0.0f, 0.0f, bird.width / 2, bird.height };

    //Sky

    Texture2D sky = LoadTextureFromImage(data->bacground_sky);
    Rectangle sky_rec = { 0.0f,0.0f, SCREEN_WIDTH,SCREEN_HEIGHT};
    Vector2 sky_position = { 0.0f,0.0f };
    UnloadImage(data->bacground_sky);

    //ground

    Texture2D ground = LoadTextureFromImage(data->ground);
    Rectangle ground_rec = { 0.0f,0.0f,SCREEN_WIDTH,ground.height };
    Vector2 ground_position = { 0.0f,SCREEN_HEIGHT - ground.height};
    UnloadImage(data->ground);

    //land

    Texture2D land = LoadTextureFromImage(data->land);
    Rectangle land_rec = { 0.0f,0.0f,SCREEN_WIDTH,land.height };
    Vector2 land_positon = { 0.0f,SCREEN_HEIGHT - land.height};

    //Pillers

    Texture2D top_piller = LoadTextureFromImage(data->piller_up);

    Texture2D bottom_piller = LoadTextureFromImage(data->piller_down);
   
    UnloadImage(data->piller_up);
    UnloadImage(data->piller_down);
    
    //score board
    Texture2D scoreBoard = LoadTextureFromImage(data->score_board);
    UnloadImage(data->score_board);
    Vector2 score_board_position = { (SCREEN_WIDTH - 2.0f * scoreBoard.width), (float)(scoreBoard.height) };

    //game over
    Texture2D gameOver = LoadTextureFromImage(data->game_over);
    UnloadImage(data->game_over);
    Rectangle game_over_rec = { 0.0f,0.0f,gameOver.width /2  , gameOver.height   };
    Vector2 gameover_position = {(SCREEN_WIDTH / 2 - game_over_rec.width),( SCREEN_HEIGHT / 2 - game_over_rec.height) };

    while (!WindowShouldClose()) {
	if((bird_position.y + bird.height) >= land_positon.y){
		game_over = true;
	}
        if (IsKeyPressed(KEY_D) and not game_over) {

            game_start = true;
        }
        else if (IsKeyPressed(KEY_R)) {
            game_start = true;
            game_over = false;
            randomGape = 0;
            top_pillar_positions = {};
            bottom_pillar_positions = {};
            Score = 0; 
            score = std::to_string(Score);
	    bird_position.x = SCREEN_WIDTH / 2 - bird.width;
	    bird_position.y = SCREEN_HEIGHT / 2 - bird.height;
        }
        if (top_pillar_positions.empty() || top_pillar_positions.back().x <= SCREEN_WIDTH - SCREEN_WIDTH / 2) {
            // Generate new pipe positions
            randomGape = GetRandomValue(1,100);
            top_pillar_positions.push_back({SCREEN_WIDTH,-300.0f - randomGape - (float) 1.5 * bird.height });
            bottom_pillar_positions.push_back({SCREEN_WIDTH, 300.0f - randomGape +(float) 1.5 * bird.height});
        }

        // Update pipe positions
        for (size_t i = 0; i < top_pillar_positions.size(); i++) {
            if (game_start and not game_over) {
                top_pillar_positions[i].x -= SPEED;
                bottom_pillar_positions[i].x -= SPEED;
            }
            if (bird_position.x >= top_pillar_positions[i].x + top_piller.width &&  bird_position.x - SPEED <= top_pillar_positions[i].x + top_piller.width) {
                Score += 5;
                score = std::to_string(Score);
            }
            // Remove pipes that are off-screen
            if (top_pillar_positions[i].x + top_piller.width < 0) {
                top_pillar_positions.erase(top_pillar_positions.begin() + i);
                bottom_pillar_positions.erase(bottom_pillar_positions.begin() + i);
                i--; // Ensure correct iteration after deletion
            }
        }
        
        
        if (game_start and not game_over) {
            sky_rec.x += 0.3 *temp_speed;
            ground_rec.x +=  0.5 *temp_speed;
            land_rec.x += 1 * temp_speed;
            
        }


        if (IsKeyDown(KEY_SPACE) and not game_over) {
            if (bird_position.y >= 0) {
                bird_position.y -= FALLDOWN;
            }

        }
        else if(IsKeyDown(KEY_S)  and not game_over) {
            if ((bird_position.y + bird.height) <= land_positon.y) {
                bird_position.y +=1.5 * FALLDOWN;
            }
        }
        else {
            if ((bird_position.y + bird.height) <= land_positon.y and game_start) {
                bird_position.y += 1.5 * FALLDOWN;
            }
        }

        frame_counter++;
        if (frame_counter >= FRAME_RATE / 10 and not game_over) {  // Adjust frame rate
            frame_counter = 0;
            print_bird.x += bird.width / 2; // Move to the next frame
        }

        ClearBackground(RAYWHITE);
        BeginDrawing();
        DrawTextureRec(sky,sky_rec,sky_position,RAYWHITE);
        DrawTextureRec(ground, ground_rec, ground_position, RAYWHITE);
       
        for (size_t i = 0; i < top_pillar_positions.size(); i++) {
            DrawTexture(top_piller, top_pillar_positions[i].x, top_pillar_positions[i].y, RAYWHITE);
            DrawTexture(bottom_piller, bottom_pillar_positions[i].x, bottom_pillar_positions[i].y, RAYWHITE);
        }
        DrawTextureRec(land, land_rec, land_positon, RAYWHITE);
        DrawTextureRec(bird, print_bird, bird_position, RAYWHITE);
        DrawTexture(scoreBoard, score_board_position.x, score_board_position.y, RAYWHITE);
        DrawText(score.c_str(), score_board_position.x + scoreBoard.width + 10, score_board_position.y - 5, 30, RED);
        if(not game_start and not game_over){
            char text[] = "press 'D' to Start.....";
            DrawText(text , SCREEN_WIDTH / 2 - 200 , SCREEN_HEIGHT/2 - 300 , 50 , BLUE);
        }
        if (game_over) {
            char restart[] = "press 'R' to Restart....";
            DrawText(restart,SCREEN_WIDTH /2 - 250, SCREEN_HEIGHT / 2 - 300 , 50 , BLUE);
        
            DrawTexture(gameOver, gameover_position.x, gameover_position.y, RAYWHITE);
        }
        for (size_t i = 0; i < top_pillar_positions.size(); i++) {
            if (((bird_position.x + bird.width / 2 -10 >= top_pillar_positions[i].x && bird_position.x <= top_pillar_positions[i].x + top_piller.width) &&
                (bird_position.y + bird.height >= top_pillar_positions[i].y && bird_position.y <= top_pillar_positions[i].y + top_piller.height))
                ) {

                game_start = false;
                game_over = true;
            }
            else if (((bird_position.x + bird.width / 2 -10 >= bottom_pillar_positions[i].x && bird_position.x <= bottom_pillar_positions[i].x + bottom_piller.width) &&
                (bird_position.y + bird.height >= bottom_pillar_positions[i].y && bird_position.y <= bottom_pillar_positions[i].y + bottom_piller.height))
                ){
                     game_start = false;
                     game_over = true;
                 }
            
        }


        EndDrawing();
    }

    UnloadTexture(bird);
    UnloadTexture(top_piller);
    UnloadTexture(bottom_piller);
    UnloadTexture(sky);
    UnloadTexture(land);
    UnloadTexture(ground);
    UnloadTexture(scoreBoard);
    UnloadTexture(gameOver);
    delete(data);
}
