using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnCoins : MonoBehaviour
{
    public GameObject Template;

    private void Start()
    {
        GameObject newObject = Instantiate(Template, new Vector3(0.7958186f, -0.1892075f, 0), Quaternion.identity);
    }

}


